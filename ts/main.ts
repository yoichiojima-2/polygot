import express, { Request, Response } from "express";

const PORT: string = "8080";
const VERSION: string = "1.0.0";

interface HealthResponse {
  language: string;
  version: string;
}

const health = (req: Request, res: Response): void => {
  const response: HealthResponse = {
    language: "ts",
    version: VERSION,
  };
  res.status(200).json(response);
};

function main() {
  const app = express();
  app.get("/health", health);

  app.listen(PORT, (): void => {
    console.log(`server running on port ${PORT}`);
  });
}

main();
