/*
 * Postfix_handler.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: muhammed
 */

#include "Postfix_handler.h"

Postfix_handler& Postfix_handler::get_Instance(){
	static Postfix_handler instance;
	return instance;
}
/*
 * Check whether the operand is Letter or number
*/
bool Postfix_handler::is_operand(char c){
	if((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			return true;
	return false;
}

/*
 * Check the operators
 */
bool Postfix_handler::is_operator(char c){
	if(c == '*' || c == '+' || c == '?' || c == '#' || c == '|')
			return true;
	return false;
}

/*
 * Returns the priority of each operation
 */
int Postfix_handler::priority(char c){
	if(c == '*' || c == '+' || c == '?')
		return 3;
	else if(c == '#')//concatenation --> must be added before converting to Postfix
		return 2;
	else if(c == '|')
		return 1;
	else return -1;
}

/*
 * convert infix expression to postfix expression
 * */
string Postfix_handler::to_postfix(vector<char> exp)
{
  stack<char> st;
  st.push('@'); //Indicating the start
  int n = exp.size();
  string output;
  for(int i=0; i<n; i++)
  {
	 char c = exp[i];
	 //If token is operand print it to ouput
	 if(is_operand(c))
	 {
		 output += c;
		 output += ' ';
	 }
	 //If token is operator check priority to
	 //make the token bigger than all the values in stack
	 else if(is_operator(c))
	 {
		 while(st.top() != '@' && st.top() != '(' &&(priority(c) <= priority(st.top())))
			{
				char temp = st.top();
			 	st.pop();
				output += temp;
				output += ' ';
			}
			st.push(c);
	 }
	 //Push opening brackets to stack
	 else if(c == '(')
	 {
		 st.push('(');
	 }
	 //If closing bracket pop all the contents from stack until
	 //opening bracket is met
	 else if(c == ')')
	 {
		 while(st.top() != '@' && st.top() != '(')
		 {
			 char temp = st.top();
	         st.pop();
	         output += temp;
	         output += ' ';
		 }
	     if(st.top() == '(')
            {
                char temp = st.top();
                st.pop();
            }

	 }
  }
  while(st.top() != '@')
      {
          char c = st.top();
          st.pop();
          output += c;
          output += ' ';
      }
 return output;
}

/*
 * Takes postfix expression and evaluate its NFA and return the starting Node of NFA
 * NOT TESTED
 * */
Node* Postfix_handler::evaluate_postfix(string exp, string token)
{   //Initialzing stack
    stack<Graph*> st;
    //Intitializing Thomson builder
    Thomson_Builder& T_builder = Thomson_Builder::get_Instance();
    int n = exp.length();
    // Scan all characters one by one
    for (int i = 0; i<n; i++)
    {   char c = exp[i];

        if (is_operator(c))
        {
           if(c == '#'){
        	   Graph* g1 = st.top(); //Operand 1
        	   st.pop();
        	   Graph* g2 = st.top(); //Operand 2
        	   st.pop();
        	   Graph* result;
               result = T_builder.concat_operation(g2,g1);
               st.push(result);
           }else if(c == '|'){
               Graph* g1 = st.top(); //Operand 1
        	   st.pop();
        	   Graph* g2 = st.top(); //Operand 2
        	   st.pop();
        	   Graph* result;
               result = T_builder.or_operation(g2,g1);
               st.push(result);
           }else if(c == '*'){
               Graph* g = st.top(); //Operand
        	   st.pop();
        	   Graph* result;
               result = T_builder.star_operation(g);
               st.push(result);
           }else if(c == '+'){
               Graph* g = st.top(); //Operand
        	   st.pop();
        	   Graph* result;
               result = T_builder.plus_operation(g);
               st.push(result);
           }
        }
        else if(is_operand(c))
        {
          string token = "";
          token += c;
          Graph* g = T_builder.initialize_graph(token);
          st.push(g);
        }
    }
    Graph* final_graph = st.top();
    st.pop();
    Node* start_node = final_graph->get_start_node();
    T_builder.save_graph(final_graph,token);
    return start_node;
}