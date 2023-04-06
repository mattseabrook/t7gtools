import ast
import os
import sys

from graphviz import Digraph


def create_graph(node, parent_node, parent_graph):
    """Recursively create nodes and edges for AST."""
    node_id = str(id(node))
    label = type(node).__name__

    # Create node
    parent_graph.node(node_id, label)

    # Create edge to parent
    if parent_node is not None:
        parent_graph.edge(parent_node, node_id)

    # Recurse on children
    for child_name, child in ast.iter_fields(node):
        if isinstance(child, list):
            for i, subnode in enumerate(child):
                if isinstance(subnode, ast.AST):
                    create_graph(subnode, node_id + str(i), parent_graph)
        elif isinstance(child, ast.AST):
            create_graph(child, node_id, parent_graph)


def create_control_flow_graph(function_name):
    # Read in the Python file and parse the AST
    with open("DecompressBlock-GPT-35.py") as file:
        code = file.read()
    module = ast.parse(code)

    # Find the function node
    function_node = None
    for node in ast.walk(module):
        if isinstance(node, ast.FunctionDef) and node.name == function_name:
            function_node = node
            break

    if function_node is None:
        print(f"Could not find function {function_name} in file")
        sys.exit(1)

    # Create the control flow graph
    graph = Digraph(comment="Control Flow Graph")
    create_graph(function_node, None, graph)

    # Render the graph to PDF
    graph.render(view=True)


if __name__ == "__main__":
    function_name = "DecompressBlock"
    create_control_flow_graph(function_name)
