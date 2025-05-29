import { handleRequest } from "./routes.ts";

console.log("HTTP webserver running. Access it at: http://localhost:8000/");

Deno.serve({ port: 8000 }, handleRequest);
