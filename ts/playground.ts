import { Client } from "pg";
import * as dotenv from "dotenv";

dotenv.config();

const DB_CONFIG = {
  user: process.env.DB_USER,
  host: process.env.DB_HOST,
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: parseInt(process.env.DB_PORT || "5432", 10),
};

interface Task {
  id: number;
  title: string;
  due: Date;
}

const query = async (): Promise<Task[]> => {
  const client = new Client(DB_CONFIG);
  try {
    await client.connect();
    const result = await client.query<Task>("select * from tasks");
    return result.rows;
  } finally {
    await client.end();
  }
};

const main = async () => {
  const tasks = await query();
  console.log(tasks);
};

main();
