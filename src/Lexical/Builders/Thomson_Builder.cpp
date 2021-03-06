/*
 * Thomson_Builder.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: muhammed
 */


#include "Thomson_Builder.h"


Graph* Thomson_Builder::initialize_graph(string val){

	Node* start = new Node;
	Node* end = new Node;

	start->set_node_number();
	end->set_node_number();

	start->add_edge(end,val);

	end->set_priority(valid);

	Graph* g = new Graph(start,end,2);

	return g;
}

Graph* Thomson_Builder::concat_operation(Graph* g1 , Graph* g2){

	g1->get_end_node()->add_edge(g2->get_start_node(),lambda);

	g1->get_end_node()->set_priority(in_valid);

	int sz = g1->get_graph_size() + g2->get_graph_size();

	Graph* g = new Graph(g1->get_start_node(),g2->get_end_node(),sz);

	return g;
}

Graph* Thomson_Builder::or_operation(Graph* g1 , Graph* g2){
/*
	Node* start = new Node;

	Node* end = new Node;

	start->set_node_number();
	end->set_node_number();

	end->set_priority(valid);

	start->add_edge(g1->get_start_node(),lambda);
	start->add_edge(g2->get_start_node(),lambda);

	g1->get_end_node()->add_edge(end,lambda);
	g1->get_end_node()->set_priority(in_valid);

	g2->get_end_node()->add_edge(end,lambda);
	g2->get_end_node()->set_priority(in_valid);

	int sz = g1->get_graph_size() + g2->get_graph_size() + 2;

	Graph* g = new Graph(start,end,sz);
	*/

	g1->get_start_node()->add_edge(g2->get_start_node(),lambda);
	g2->get_end_node()->add_edge(g1->get_end_node(),lambda);

	int sz = g1->get_graph_size() + g2->get_graph_size();

	g1->set_graph_size(sz);

	return g1;
}


Graph* Thomson_Builder::star_operation(Graph* g1){
/*
	Node* start = new Node;
	Node* end = new Node;

	start->set_node_number();
	end->set_node_number();

	end->set_priority(valid);

	g1->get_end_node()->set_priority(in_valid);

	g1->get_end_node()->add_edge(end,lambda);

	start->add_edge(g1->get_start_node(),lambda);

	g1->get_end_node()->add_edge(g1->get_start_node(),lambda);

	start->add_edge(end,lambda);

	int sz = g1->get_graph_size() + 2;

	Graph* g = new Graph(start,end,sz);
*/
	g1->get_start_node()->add_edge(g1->get_end_node(),lambda);
	g1->get_end_node()->add_edge(g1->get_start_node(),lambda);
	return g1;
}

Graph* Thomson_Builder::plus_operation(Graph* g1){
/*
	Node* start = new Node;
	Node* end = new Node;

	start->set_node_number();
	end->set_node_number();

	end->set_priority(valid);

	g1->get_end_node()->set_priority(in_valid);

	g1->get_end_node()->add_edge(end,lambda);

	start->add_edge(g1->get_start_node(),lambda);

	g1->get_end_node()->add_edge(g1->get_start_node(),lambda);

	int sz = g1->get_graph_size() + 2;

	Graph* g = new Graph(start,end,sz);
*/
	g1->get_end_node()->add_edge(g1->get_start_node(),lambda);

	return g1;
}

Graph* Thomson_Builder::range_operation(Graph* g1 , Graph* g2) {

	int start_range = (int)string_to_char(g1->get_start_node()->get_edges().begin()->get_value());
	int end_range =  (int)string_to_char(g2->get_start_node()->get_edges().begin()->get_value());

	Graph* g = or_operation(g1,g2);

	Node* start = g->get_start_node();
	Node* end = g->get_end_node();

	for(int i = start_range+1; i < end_range ; i++){
		start->add_edge(end,char_to_string((char)i));
	}

	return g1;
}

void Thomson_Builder::save_graph(Graph* g,string token){

	g->get_end_node()->set_token(token);
	saved_graphs.push_back(g);
}

Node* Thomson_Builder::assemble_saved_graphs(){
	Node* start = new Node;

	start->set_node_number();

	for(unsigned int i = 0 ; i < saved_graphs.size() ; i++){
		start->add_edge(saved_graphs[i]->get_start_node(),lambda);
	}
	return start;
}

Thomson_Builder& Thomson_Builder::get_Instance(){
	static Thomson_Builder instance;
	return instance;
}
