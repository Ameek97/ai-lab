# Backward Chaining

facts = ["A", "B"]
# This is our initial knowledge base. We already know that A and B are true.

rules = [
    (["A", "B"], "C"),
    (["C"], "D"),
    (["D"], "E")
]

def backward_chaining(goal):
    if goal in facts:
        return True

    for condition, conclusion in rules:
        if conclusion == goal:
            if all(backward_chaining(fact) for fact in condition):
                return True

    return False

goal = "E"

if backward_chaining(goal):
    print("Goal", goal, "can be proved")
else:
    print("Goal", goal, "cannot be proved")