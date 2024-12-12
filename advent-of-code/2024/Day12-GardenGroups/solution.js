const fs = require('fs');
const readline = require('readline');

function inBounds(i, j, map) {
  return i >= 0 && i < map.length && j >= 0 && j < map[0].length;
}

function dfs(map, i, j, visited, area) {
  if (visited.has(`${i},${j}`)) {
    return 0;
  }
  if (!inBounds(i, j, map) || map[i][j] !== area) {
    return 1;
  }
  visited.add(`${i},${j}`);
  const neighbors = [[i-1, j], [i+1, j], [i, j-1], [i, j+1]];
  let result = 0;
  for (let [ni, nj] of neighbors) {
    result += dfs(map, ni, nj, visited, area);
  }
  return result;
}

function dfs2(map, i, j, visited, area, sidesSet) {
  if (visited.has(`${i},${j}`)) {
    return;
  }
  visited.add(`${i},${j}`);
  const neighbors = [[i-1, j], [i+1, j], [i, j-1], [i, j+1]];
  for (let [ni, nj] of neighbors) {
    if (!inBounds(ni, nj, map) || map[ni][nj] !== area) {
      sidesSet.add(`${i},${j}|${ni},${nj}`);
    } else {
      dfs2(map, ni, nj, visited, area, sidesSet);
    }
  }
  return;
}

function part1(map) {
  let visited = new Set();
  let result = 0;
  for (let i = 0; i < map.length; i++) {
    for (let j = 0; j < map[i].length; j++) {
      if (visited.has(`${i},${j}`)) {
        continue;
      }
      const areaSet = new Set();
    
      const perimeter = dfs(map, i, j, areaSet, map[i][j]);

      result += perimeter * areaSet.size;
      visited = new Set([...visited, ...areaSet]);
    }
  }
  return result
}

function dfs3(map, side, visited, sidesSet) {
  if (visited.has(side)) {
    return 0;
  }
  visited.add(side);
  const [left, right] = side.split('|');
  const [i, j] = left.split(',').map(Number);
  const [ni, nj] = right.split(',').map(Number);
  
  let neighbors = [
    `${i+1},${j}|${ni+1},${nj}`, 
    `${i-1},${j}|${ni-1},${nj}`, 
    `${i},${j-1}|${ni},${nj-1}`,
    `${i},${j+1}|${ni},${nj+1}`
  ] 
  for (let next of neighbors) {   
    if (sidesSet.has(next)) {
      dfs3(map, next ,visited, sidesSet);
    }
  }
  return 1;
}

function getSides(map, sidesSet) {
  
  let result = 0;
  let visited = new Set();
  sidesSet.forEach(side => {
    result += dfs3(map, side, visited, sidesSet);
  })
  return result
}

function part2(map) {
  let visited = new Set();
  let result = 0;
  for (let i = 0; i < map.length; i++) {
    for (let j = 0; j < map[i].length; j++) {
      if (visited.has(`${i},${j}`)) {
        continue;
      }
      const areaSet = new Set();
      const sidesSet = new Set()
      dfs2(map, i, j, areaSet, map[i][j], sidesSet);
      const sides = getSides(map, sidesSet);
      
      result += sides * areaSet.size;
      visited = new Set([...visited, ...areaSet]);
    }
     
  }
  return result
}

async function processLineByLine() {
  const fileStream = fs.createReadStream('input.txt');

  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity
  });

  let map = [];
  
  for await (const line of rl) {
      map.push(line.split(''));
  }

  console.log("🚀 ~ processLineByLine", part2(map))
}

processLineByLine();