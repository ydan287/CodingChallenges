const fs = require('fs');
const readline = require('readline');

isValidToplogicalOrder = (graph, order) => {
    const orderSet = new Set(order);
    for (let i = 0; i < order.length; i++) {
        const node = order[i];
        if (graph[node]) {
            for (let neighbor of graph[node]) {
                if (orderSet.has(neighbor)) {
                    return false;
                }
            }
        }
        orderSet.delete(node);
    }
    return true;
}

function fixTopologicalOrder(graph, order) {
    
    if (isValidToplogicalOrder(graph, order)) {
        return order;
    }
    const orderSet = new Set(order);
    const newOrderSet = new Set();
    for (let i = 0; i < order.length; i++) {
        const node = order[i];
        if (graph[node]) {
            for (let neighbor of graph[node]) {
                if (orderSet.has(neighbor)) {
                    newOrderSet.add(neighbor);
                }
            }
        }
        newOrderSet.add(node);
        orderSet.delete(node);
    }
    return fixTopologicalOrder(graph, [...newOrderSet]);
}
    

function createGraphFromEgdes(edges) {
    const graph = {};
    for (let [from, to] of edges) {
        if (!graph[to]) {
            graph[to] = [];
        }
        graph[to].push(from);
    }
    return graph;
}

function solution(edges, subLists) {
    const graph = createGraphFromEgdes(edges);
    const correctUpdates = subLists.filter(list => isValidToplogicalOrder(graph, list));
    let sum = 0;
    
    correctUpdates.forEach(list => {
        let middle = list[Math.floor(list.length / 2)]
        sum += parseInt(middle);
    });
        
    return sum;
}

function part2(edges, subLists) {
    const graph = createGraphFromEgdes(edges);
    const incorrectUpdates = subLists.filter(list => !isValidToplogicalOrder(graph, list)).map(list => fixTopologicalOrder(graph, list));
    let sum = 0;
    
    incorrectUpdates.forEach(list => {
        let middle = list[Math.floor(list.length / 2)]
        sum += parseInt(middle);
    });
    return sum;

}

async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    const edges = [];
    
    const subLists = [];
    
    
    for await (const line of rl) {
        if (line.includes('|')) {
            const [from, to] = line.split('|');
            edges.push([from, to]);
        } else if (line.includes(',')){
            const list = line.split(',');
            subLists.push(list);
        }
    }
    console.log("🚀 ~ processLineByLine ~ part1:", solution(edges, subLists))
    console.log("🚀 ~ processLineByLine ~ part2:", part2(edges, subLists))
}

     

  
  processLineByLine();

  
