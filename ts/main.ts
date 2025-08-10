import express, { Request, Response } from "express";
import { Task, getAllTasks } from "./tasks";

const PORT: string = "8080";
const VERSION: string = "1.0.0";

interface HealthResponse {
  language: string;
  version: string;
}

interface TasksResponse {
  tasks: Task[];
  count: number;
}

const health = (req: Request, res: Response): void => {
  const response: HealthResponse = {
    language: "ts",
    version: VERSION,
  };
  res.status(200).json(response);
};

const tasks = async (req: Request, res: Response): Promise<void> => {
  try {
    const allTasks = await getAllTasks();
    const response: TasksResponse = {
      tasks: allTasks,
      count: allTasks.length,
    };
    res.status(200).json(response);
  } catch (error) {
    console.error("error fetching tasks: ", error);
    res.status(500).json({ error: "failed to fetch tasks" });
  }
};

function main() {
  const app = express();
  app.get("/health", health);
  app.get("/tasks", tasks);

  app.listen(PORT, (): void => {
    console.log(`server running on port ${PORT}`);
  });
}

main();
