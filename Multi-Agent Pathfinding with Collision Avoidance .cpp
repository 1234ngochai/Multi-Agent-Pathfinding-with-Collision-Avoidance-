void ALevelGeneratorCalculatePath()
{
    UE_LOG(LogTemp, Warning, TEXT(Starting A Path Calculation));

    EnsureCurrentNodeForShips();

     Define a lambda for comparing nodes in the priority queue by their F value (G + H)
    auto CompareNodes = [](GridNode a, GridNode b) { return a-F  b-F; };

    for (AShip Ship  Ships)
    {
    	stdpriority_queueGridNode, stdvectorGridNode, decltype(CompareNodes) queue(CompareNodes);
    	ResetAllNodes();
         Reset distances, parent pointers, and heuristic values for all nodes
        for (int y = 0; y  MAX_MAP_SIZE; y++)
        {
            for (int x = 0; x  MAX_MAP_SIZE; x++)
            {
                GridNode node = WorldArray[y][x];
                if (node)
                {
                    node-G = 100000;  Initially high G value
                    node-H = CalculateHeuristic(node, Ship-GoalNode);  Manhattan distance as heuristic
                    node-F = node-G + node-H;
                    node-Parent = nullptr;
                }
            }
        }

        GridNode startNode = Ship-CurrentNode;
        startNode-G = 0;
        startNode-F = startNode-G + startNode-H;
        queue.push(startNode);

        while (!queue.empty())
        {
            GridNode current = queue.top();
            queue.pop();
        	SearchCount++;

            if (current == Ship-GoalNode) break;

            TArrayGridNode neighbors = GetNeighbors(current);

            for (GridNode neighbor  neighbors)
            {
                float tentativeG = current-G + neighbor-GetTravelCost();
                float tentativeF = tentativeG + neighbor-H;  F = G + H

                if (tentativeF  neighbor-F)
                {
                    neighbor-Parent = current;
                    neighbor-G = tentativeG;
                    neighbor-F = tentativeF;

                     A node may be added to the queue multiple times with different F values;
                     we only care about the smallest one.
                    queue.push(neighbor);
                }
            }
        }
    	
        RenderPath(Ship);  Visualize the path
    }

    UE_LOG(LogTemp, Warning, TEXT(Finished A Path Calculation));
}