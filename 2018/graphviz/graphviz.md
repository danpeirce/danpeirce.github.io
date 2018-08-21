% Graphviz
% Notes by Dan Peirce B.Sc.
%

# Graphviz

When looking for a method of automating the creation of state transition drawings
I came across Graphvis. It looked promising so I decided to keep notes. The 
fist example I found that was essentially what I was looking for was here:

* [http://tonyballantyne.com/graphs.html#sec-6-1](http://tonyballantyne.com/graphs.html#sec-6-1)

I modified that example for my needs.

## First use of Graphviz and Dot

My first Graphviz Dot file:

~~~~dot
digraph finite_state_machine {
        //rankdir=LR;
        size="8,10"
        //graph [ranksep="0.525", nodesep="0.5"];
        start [shape=point, xlabel=<Take points at top and<br /> bottom as same point.>];
        end [shape=point];
        //node [shape = circle];
        start -> defaultS
        defaultS -> op1;
        
        op1 -> stopwatchS [ label = "Sel SW" ]
        stopwatchS -> end [ label = "Reset SW" ]
        op2 -> photogateM1S [ label = "Sel Photogate" ]
        photogateM1S -> end [ label = "Reset SW" ]
        op3 -> photogateM2S [ label = <Sel SWPendulum> ]
        photogateM2S -> end [ label = "Reset SW" ]
        op4 -> pulseS [ label = "Sel SW" ]
        pulseS -> end [ label = "Reset SW" ]
        pulseS -> keepS [label = "second edge" ]
        keepS -> op1;
        op5 -> picketfence1S [ label = "Sel SW" ]
        picketfence1S -> end [ label = "Reset SW" ]
        picketfence1S -> cycleTimesS [ label = "All Edges Detected" ]
        cycleTimesS -> end [ label = "Reset SW" ]
        subgraph cluster_mode {
                 rankdir=TB;
                 node [shape = circle];
                 op1 -> op2;
                 op2 -> op3;
                 op3 -> op4;
                 op4 -> op5;
                 op5 -> op1;
                 label = "modeS";
        } 
}

/*
dot -Tpng pickmode.gv -o pickmode.png
*/
~~~~

Graphviz produced the following image for the state transition diagram:

![](pickmode.png)

### Inconsistent use of Semicolons

One issue I noticed when the the initial example to others was the use of semicolons
was not consistant. When searching for an explination for this I found:

~~~~
Semicolons and commas aid readability but are not required.
~~~~

* that from [https://www.graphviz.org/doc/info/lang.html](https://www.graphviz.org/doc/info/lang.html)

<!---
use 
  pandoc -s --toc --toc-depth=5 -t html5 -c ../../pandocbd.css graphviz.md -o graphviz.html
  pandoc -t markdown_github -s --toc --toc-depth=5 -o readme.md graphviz.md
-->
