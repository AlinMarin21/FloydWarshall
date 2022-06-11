////

const graphContainer = document.querySelector('#graph-container');
const distancesContainer = document.querySelector('#distances-container');

const graphMatrix = document.querySelector('#graph-matrix');
const distancesMatrix = document.querySelector('#distances-matrix');

const tablesContainer = document.querySelector('#tables-container');

const runFWButton = document.querySelector('#run-fw-button');

const pathContainer = document.querySelector('#path-container');

const fromNodeInput = document.querySelector('#from-node-input');
const toNodeInput = document.querySelector('#to-node-input');
const seePathButton = document.querySelector('#see-path-button');

const pathText = document.querySelector('#path');

////

const INF = 99999;
let path = [];
let string_text;

document.getElementById('inputfile').addEventListener('change', function() {
              
    var fr=new FileReader();
    fr.onload=function(){
        string_text = fr.result.split(/(\r\n| )+/);

        string_text = arrayRemove(string_text, ' ');
        string_text = arrayRemove(string_text, '\r\n');
        string_text = arrayRemove(string_text, '');
    }
      
    fr.readAsText(this.files[0]);
})

function arrayRemove(arr, value) { 

    return arr.filter(function(ele){ 
    return ele != value; 
});
}

function initialise_matrix(matrix, no_of_nodes, no_of_edges) {
    for(let i = 1; i <= no_of_nodes; i++)
    {
        for(let j = 1; j <= no_of_nodes; j++)
        {
            if(i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                matrix[i][j] = INF;
            }
        }
    }
    for(let i = 2; i <= no_of_edges * 3; i = i + 3)
    {
        let node1 = parseInt(string_text[i]);
        let node2 = parseInt(string_text[i+1]);
        let cost = parseInt(string_text[i+2]);

        matrix[node1][node2] = cost;
    }
}

function display_matrix(matrix, no_of_nodes, table) {
    
    let newRow = document.createElement("tr");

    let cell = document.createElement("td");
    let cellContent = document.createTextNode("Nodes");

    cell.appendChild(cellContent);

    newRow.appendChild(cell);

    for(let i = 1; i <= no_of_nodes; i++)
    {
        cell = document.createElement("td");
        cellContent = document.createTextNode(i);

        cell.appendChild(cellContent);

        newRow.appendChild(cell);
    }

    table.appendChild(newRow);

    for(let i = 1; i <= no_of_nodes; i++)
    {
        newRow = document.createElement("tr");

        for(let j = 0; j <= no_of_nodes; j++)
        {
            cell = document.createElement("td");

            if(j == 0)
            {
                cellContent = document.createTextNode(i);
            }
            else
            {
                if(matrix[i][j] == INF)
                {
                    cellContent = document.createTextNode("-");
                }
                else
                {
                    cellContent = document.createTextNode(matrix[i][j]);
                }
            }

            cell.appendChild(cellContent);

            newRow.appendChild(cell);
        }

        table.appendChild(newRow);

    }
}

function copy_matrix(copy, matrix, no_of_nodes) {
    for(let i = 1; i <= no_of_nodes; i++)
    {
        for(let j = 1; j <= no_of_nodes; j++)
        {
            copy[i][j] = matrix[i][j];
        }
    }
}

function FloydWarshall(distances, no_of_nodes) {
    for(let k = 1; k <= no_of_nodes; k++)
    {
        for(let i = 1; i <= no_of_nodes; i++)
        {
            for(let j = 1; j <= no_of_nodes; j++)
            {
                if(distances[i][j] > distances[i][k] + distances[k][j])
                {
                    distances[i][j] = distances[i][k] + distances[k][j]
                }
            }
        }
    }
}

function compute_path(n1, n2, matrix, no_of_nodes) {
    
    let ok = 0;
    let k = 1;


    while(k <= no_of_nodes && !ok)
    {
        if(n1 != k && n2 != k)
        {
            if(matrix[n1][n2] == matrix[n1][k] + matrix[k][n2])
            {
                compute_path(n1, k, matrix, no_of_nodes);
                compute_path(k, n2, matrix, no_of_nodes);
                ok = 1;
            }
        }
        k++;
    }
    if(!ok)
    {
        path.push(n2);
    }
}

function print_path(n1, n2, matrix, no_of_nodes) {
    path = [];
    pathText.innerHTML = '';
    
    if(matrix[n1][n2] < INF)
    {
        path.push(n1);
        compute_path(n1, n2, matrix, no_of_nodes);

        let pathContent = document.createTextNode('The path from ' + n1 + ' to ' + n2 + ' has the weight ' + matrix[n1][n2]);
        pathText.appendChild(pathContent);

        let newLine = document.createElement('br');
        
        pathText.appendChild(newLine);

        pathContent = document.createTextNode('The minimum cost path is: ');
        pathText.appendChild(pathContent);

        pathContent = document.createTextNode(path[0]);
        pathText.appendChild(pathContent);

        for(let i = 1; i < path.length; i++)
        {
            pathContent = document.createTextNode(' - ' + path[i]);
            pathText.appendChild(pathContent);
        }
    }
    else
    {
        let pathContent = document.createTextNode('There is no path between ' + n1 + ' and ' + n2);
        pathText.appendChild(pathContent);
    }
}

runFWButton.addEventListener("click", function() {

    graphMatrix.innerHTML = '';
    distancesMatrix.innerHTML = '';

    document.getElementById("network-container").style.display = "none";

    pathText.style.display = "none";
    
    let no_of_nodes = parseInt(string_text[0]);
    let no_of_edges = parseInt(string_text[1]);

    let distances = [];
    for(let i = 1; i <= no_of_nodes; i++)
    {
        distances[i] = [];
        for(let j = 1; j <= no_of_nodes; j++)
        {
            distances[i][j] = undefined;
        }
    }

    let copy = [];
    for(let i = 1; i <= no_of_nodes; i++)
    {
        copy[i] = [];
        for(let j = 1; j <= no_of_nodes; j++)
        {
            copy[i][j] = undefined;
        }
    }

    initialise_matrix(distances, no_of_nodes, no_of_edges);

    copy_matrix(copy, distances, no_of_nodes);

    let start = performance.now();

    FloydWarshall(distances, no_of_nodes);

    let end = performance.now();

    console.log('Time for FW: ' + (end - start) * 1000 + " microseconds");
    console.log('Time for FW: ' + (end - start) + " milliseconds");
    console.log('Time for FW: ' + (end - start) / 1000 + " seconds");

    console.log("Distances Matrix");
    console.table(copy);
    console.log("APSP Matrix");
    console.table(distances);

    if(no_of_nodes <= 50)
    {
        tablesContainer.style.display = "flex";

        display_matrix(copy, no_of_nodes, graphMatrix);
        display_matrix(distances, no_of_nodes, distancesMatrix);
    }

    pathContainer.style.display = "block";

    if(no_of_nodes <= 20)
    {
        document.getElementById("network-container").style.display = "block";

        let nodes, edges, network;

        draw(nodes, edges, network, copy, no_of_nodes);
    }

    seePathButton.addEventListener("click", function() {
        let n1 = parseInt(fromNodeInput.value);
        let n2 = parseInt(toNodeInput.value);

        pathText.style.display = "block";

        print_path(n1, n2, distances, no_of_nodes);

    });

});

function draw(nodes, edges, network, matrix, no_of_nodes) {
    nodes = new vis.DataSet();

    for(let i = 1; i <= no_of_nodes; i++)
    {
        nodes.add({
            id: i.toString(),
            label: i.toString(),
        });
    }

    edges = new vis.DataSet();

    for(let i = 1; i <= no_of_nodes; i++)
    {
        for(let j = 1; j <= no_of_nodes; j++)
        {
            if(matrix[i][j] != 0 && matrix[i][j] != INF)
            {
                edges.add({
                    from: i.toString(),
                    to: j.toString(),
                    label: matrix[i][j].toString(),
                    arrows: 'to',
                    color: 'green',
                });
            }
        }
    }

    var container = document.getElementById("network-container");

    var data = {
        nodes: nodes,
        edges: edges,
    };
    var options = {};
    network = new vis.Network(container, data, options);
}
