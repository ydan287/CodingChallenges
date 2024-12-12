const { assert } = require('console');
const fs = require('fs');
const readline = require('readline');

function sumOfRange(start, size) {
  if (!size) {
    return 0;
  }
  let sum = start;
  for (let i = 1; i < size; i++) {
    sum += start+i;
  }
  return sum;
}

function solution1(disk) {
  // [id, start, size]
  // -1 is used for the empty space
  let files = [];  
  // [start, size]
  let freeSpaces = [];
  let moreFiles = [];
  
  let id = 0;
  let index = 0;
  for (let i = 0; i < disk.length; i+=2) {

    files.push({id: id++,start: index,size: Number(disk[i])})
    index += Number(disk[i]);
    if (disk[i+1]) {
      freeSpaces.push({start: index, size: Number(disk[i+1])})
      index += Number(disk[i+1]);
    }
  }
  // console.log("🚀 ~ solution1 ~ files:", files)
  // console.log("🚀 ~ solution1 ~ freeSpaces:", freeSpaces)
  let lastFile = files[files.length - 1];
  let firstFreeSpace = freeSpaces[0];
  while(lastFile.start > firstFreeSpace.start) {
    if (lastFile.size === firstFreeSpace.size) {
      moreFiles.push({id: lastFile.id, start: firstFreeSpace.start, size: lastFile.size})
      files.pop();
      freeSpaces.shift();
    } else if (lastFile.size < firstFreeSpace.size) {
      moreFiles.push({id: lastFile.id, start: firstFreeSpace.start, size: lastFile.size})
      files.pop();
      firstFreeSpace.start += lastFile.size;
      firstFreeSpace.size -= lastFile.size;
    } else {
      moreFiles.push({id: lastFile.id, start: firstFreeSpace.start, size: firstFreeSpace.size})
      lastFile.size -= firstFreeSpace.size;
      freeSpaces.shift();
    }

    lastFile = files[files.length - 1];
    firstFreeSpace = freeSpaces[0];
    
  }
  let sum = 0;


  files.concat(moreFiles).sort((a, b) => a.start - b.start).forEach(file => {
      console.log("🚀 ~ files.concat ~ file:", file)
      sum += file.id * sumOfRange(file.start, file.size);
      console.log("🚀 ~ files.concat ~ sumOfRange(file.start, file.size):", sumOfRange(file.start, file.size))
    });
    
    return sum;
}

function solution2(disk) {
  // [id, start, size]
  // -1 is used for the empty space
  let files = [];  
  // [start, size]
  let freeSpaces = [];
  let moreFiles = [];
  
  
  let id = 0;
  let index = 0;
  for (let i = 0; i < disk.length; i+=2) {

    files.push({id: id++,start: index,size: Number(disk[i])})
    index += Number(disk[i]);
    if (disk[i+1]) {
      freeSpaces.push({start: index, size: Number(disk[i+1])})
      index += Number(disk[i+1]);
    }
  }
  
  for(let i = files.length -1; i >=0 ; i--) {
    for (let j = 0 ; j < freeSpaces.length; j++) {
      if (files[i].start > freeSpaces[j].start && files[i].size <= freeSpaces[j].size) {
        
        files[i].start = freeSpaces[j].start;
        files[i].moved = true;
        freeSpaces[j].start += files[i].size;
        freeSpaces[j].size -= files[i].size;
        break;
      }
    }
  }
  
  let sum = 0;


  files.concat(moreFiles).sort((a, b) => a.start - b.start).forEach(file => {
      sum += file.id * sumOfRange(file.start, file.size);
    });
    
    return sum;
}


async function processLineByLine() {
    const fileStream = fs.createReadStream('input.txt');
  
    const rl = readline.createInterface({
      input: fileStream,
      crlfDelay: Infinity
    });

    let disk = ''
    
    for await (const line of rl) {
        disk = line;
    }

    // console.log("🚀 ~ processLineByLine ~ assert(solution1('12345') === 60):", solution1('12345'))
    // console.log("🚀 ~ processLineByLine ~ assert(solution1('20202') === 23):", solution1('20202'))
    // assert(solution2('2333133121414131402') === 1928)
    console.log("🚀 ~ processLineByLine", solution2(disk))
}

     

  
  processLineByLine();

  
