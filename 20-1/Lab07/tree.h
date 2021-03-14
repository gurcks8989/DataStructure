typedef 
	struct _node_t {
		char data[64] ;
		struct _node_t * child ; // left
		struct _node_t * sibling ; // right
	} 
	node_t ;

typedef struct _node_t tree_t ;

node_t * 
tree_create_node (char data[64]) ;

node_t *
tree_add_child (node_t * parent, node_t * child) ;

int
tree_height(tree_t * t) ;

node_t *
tree_search (node_t * t, char key[64]) ;

void
tree_print (tree_t * t) ;
