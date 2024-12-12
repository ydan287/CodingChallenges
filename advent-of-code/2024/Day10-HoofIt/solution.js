const { assert } = require('console');
const fs = require('fs');
const readline = require('readline');


function getSetOfCharPositions(map) {
  const set0 = new Set();
  const set9 = new Set();
  for (let i = 0; i < map.length; i++) {
    for (let j = 0; j < map[i].length; j++) {
      if (map[i][j] === '0') {
        set0.add(`${i},${j}`)
      }
      if (map[i][j] === '9') {
        set9.add(`${i},${j}`)
      }
    }
  }
  return [set0, set9];
}

function inBounds(i, j, map) {
  return i >= 0 && i < map.length && j >= 0 && j < map[0].length;
}

function updateScoreMap(map, scoreMap, pos, visited) {
  
  const [i, j] = pos.split(',').map(Number);
  visited.add(pos);
  if (scoreMap.has(pos)) {
    scoreMap.set(pos, scoreMap.get(pos) + 1);
  } else {
    scoreMap.set(pos, 1);
  }
  if (map[i][j] === '0') {
    return;
  }
  const neighbors = [[i-1, j], [i+1, j], [i, j-1], [i, j+1]];
  for (let [ni, nj] of neighbors) {
    if (inBounds(ni, nj, map) && (Number(map[ni][nj]) === Number(map[i][j]) -1) && !visited.has(`${ni},${nj}`)) {
      updateScoreMap(map, scoreMap, `${ni},${nj}`, visited);
    }
  }
}

function updateRatingMap(map, ratingMap, pos) {
  const [i, j] = pos.split(',').map(Number);
  if (ratingMap.has(pos)) {
    ratingMap.set(pos, ratingMap.get(pos) + 1);
  } else {
    ratingMap.set(pos, 1);
  }
  if (map[i][j] === '0') {
    return;
  }
  const neighbors = [[i-1, j], [i+1, j], [i, j-1], [i, j+1]];
  for (let [ni, nj] of neighbors) {
    if (inBounds(ni, nj, map) && (Number(map[ni][nj]) === Number(map[i][j]) -1)) {
      updateRatingMap(map, ratingMap, `${ni},${nj}`);
    }
  }
}

function solution1(map) {
  const [set0, set9] = getSetOfCharPositions(map);

  const scoreMap = new Map();
  const ratingMap = new Map();
  set9.forEach((pos) => {
    // updateScoreMap(map, scoreMap, pos, new Set());
    updateRatingMap(map, ratingMap, pos);
  });
  let sum = 0;
  set0.forEach((pos) => {
    if (ratingMap.has(pos)) {
      sum += ratingMap.get(pos)
    }
  });
  return sum;
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
        console.log("🚀 ~ forawait ~ map:", map)

    console.log("🚀 ~ processLineByLine", solution1(map))
}

     

  
  processLineByLine();

  
