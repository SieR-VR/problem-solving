const { readFileSync } = require("node:fs");
const input = readFileSync("/dev/stdin", "utf-8").trim();

const isSnakeCase = /^[a-z]+(_[a-z]+)*$/;
const isCamelCase = /^[a-z]+([A-Z][a-z]*)*$/;

function toSnakeCase(input) {
  return input.replace(/([A-Z])/g, "_$1").toLowerCase();
}

function toCamelCase(input) {
  return input.replace(/_([a-z])/g, (match, p1) => p1.toUpperCase());
}

if (isSnakeCase.test(input)) {
  console.log(toCamelCase(input));
} else if (isCamelCase.test(input)) {
  console.log(toSnakeCase(input));
} else {
  console.log("Error!");
}
