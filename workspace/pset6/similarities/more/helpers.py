from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""

    # Create a matrix to store cost and operations
    matrix = [[0] * (len(b) + 1) for i in range(len(a) + 1)]

    # Calculate cost and operations of transforming nothing to 'b' to
    for i in range(len(b)):
        matrix[0][i + 1] = i + 1, Operation.INSERTED
    # Calculate cost and operations of transforming 'a' to nothing
    for i in range(len(a)):
        matrix[i + 1][0] = i + 1, Operation.DELETED
    # Cost and operations if both strings are empty
    matrix[0][0] = 0, None

    # Calculate cost and operations of rest of matrix
    for i in range(len(a)):
        for j in range(len(b)):

            # Calculate the possible operations
            substitute = matrix[i][j][0] if a[i] == b[j] else matrix[i][j][0] + 1
            insert = matrix[i + 1][j][0] + 1
            delete = matrix[i][j + 1][0] + 1

            # Calculate the most efficient operation
            operation = min(substitute, insert, delete)

            # Make tuple to return
            if operation == substitute:
                operation = substitute, Operation.SUBSTITUTED
            elif operation == insert:
                operation = insert, Operation.INSERTED
            else:
                operation = delete, Operation.DELETED

            matrix[i + 1][j + 1] = operation

    return matrix
