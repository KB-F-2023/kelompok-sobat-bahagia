import time

state_dict = {}
def move_up(state):
 new_state = state[:]
 index = new_state.index(0)
 if index not in [goal_state[0], goal_state[1], goal_state[2]]:
    new_state[index], new_state[index - 3] = new_state[index - 3], new_state[index]
    return new_state
 else:
    return None

def move_down(state):
 new_state = state[:]
 index = new_state.index(0)
 if index not in [goal_state[6], goal_state[7], goal_state[8]]:
    new_state[index], new_state[index + 3] = new_state[index + 3], new_state[index]
    return new_state
 else:
    return None

def move_left(state):
 new_state = state[:]
 index = new_state.index(0)
 if index not in [goal_state[0], goal_state[3], goal_state[6]]:
    new_state[index], new_state[index - 1] = new_state[index - 1], new_state[index]
    return new_state
 else:
    return None

def move_right(state):
 new_state = state[:]
 index = new_state.index(0)
 if index not in [goal_state[2], goal_state[5], goal_state[8]]:
    new_state[index], new_state[index + 1] = new_state[index + 1], new_state[index]
    return new_state
 else:
    return None



def create_node(state, parent, operator, depth, cost):
 return Node(state, parent, operator, depth, cost)


def expand_node(node, nodes):
 expanded_nodes = []
 expanded_nodes.append(create_node(move_down(node.state), node, "Down", node.depth + 1, 0))
 expanded_nodes.append(create_node(move_up(node.state), node, "Up", node.depth + 1, 0))
 
 expanded_nodes.append(create_node(move_right(node.state), node, "Right", node.depth + 1, 0))
 expanded_nodes.append(create_node(move_left(node.state), node, "Left", node.depth + 1, 0))
 
 expanded_nodes = [node for node in expanded_nodes if node.state is not None]
 return expanded_nodes

class Node:
  def __init__(self, state, parent, operator, depth, cost):
    self.state = state
    self.parent = parent
    self.operator = operator
    self.depth = depth
    self.cost = cost

def dfs(start,goal):
 # A list (can act as a stack too) for the nodes.
 nodes = []
 visited = []
 depth_limit = 5000
 # Create the queue with the root node in it.
 nodes.append(create_node(start, None, None, 0, 0))
 start_time = time.time()
 while len(nodes) > 0:
    elapsed_time = time.time() - start_time
    if (elapsed_time < 80):
    # We've run out of states, no solution.
        if len(nodes) == 0: return None
    # take the node from the front of the queue
        node = nodes.pop(0)
    #state_str = "".join(str(n) for n in node.state)
        state_str = "".join(str(n) for n in node.state)
        if state_str in state_dict:
            continue
        state_dict[state_str] = True
        visited.append(node)
    # if this node is the goal, return the moves it took to get here.
    # print(node.state)
        for i in range(9):
            if i==3 or i==6:
                print("")
            
            temp = node.state[i]
            print(temp, end="")
            if i==8:
                print("\n")
                
        if node.state == goal:
            moves = []
            temp = node
            print(temp.depth)
            while True:
                moves.insert(0, temp.operator)
                if temp.depth <= 1: break
                temp = temp.parent
            return moves
    # Add all the expansions to the beginning of the stack if we are under the depth limit
        if node.depth < depth_limit:
            expanded_nodes = expand_node(node, nodes)
            if(expanded_nodes not in visited):
                expanded_nodes.extend(nodes)
                nodes = expanded_nodes
    else:
        return None

goal_state = [1, 4, 5, 7, 3, 2, 6, 0, 8]
start = [1, 4, 5, 0, 3, 2, 7, 6, 8]
dfs(start, goal_state)