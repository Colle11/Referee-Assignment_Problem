EasyLocal++ workflow

1. Define Input class:
    - constructor that takes the file name
	
2. Define Output class:	
    - constructor that takes

3. Define State class:
   - main data structures
   - redundant data structures (invariant) [for accelerating delta evaluations] 
   - equality operator == [for debugging]
   - constructor that takes input as parameter
   
4. Define Move class: [This step must be repeated if more than one move is defined]
   - move attributes
   - constructor that initializes the attributes
   - operators: ==, !=, <   [for the tester]
   
5. Define StateManager class:
   - RandomState
   - CheckConsistency [optional]
   
6. Define OutputManager class:
   - InputState
   - OutputState
   
7. Define NeighborhoodExplorer class:
   - FirstMove
   - NextMove
   - RandomMove
   - MakeMove
   - FeasibleMove [optional]
   
8. Define CostComponent classes (one for each cost component):
   - ComputeCost
   - PrintViolations
   
9. Define DeltaCostComponent classes (one for each cost component):
   - ComputeDeltaCost
   
10. Write the main() function including:
   - definition of command-line parameters
   - declaration of the Input object
   - declaration of helper objects
   - links between helper objects (e.g. AddCostComponent)
   - declaration of runner, solver, and tester objects
   - invocation tester or solver
   