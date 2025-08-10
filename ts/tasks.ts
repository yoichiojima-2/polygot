import { Client } from "pg";
import { DB_CONFIG } from "./sql";

// query to postgres
export interface Task {
  id: number;
  title: string;
  due: Date;
}

export const getAllTasks = async (): Promise<Task[]> => {
  const client = new Client(DB_CONFIG);
  try {
    await client.connect();
    const result = await client.query<Task>("select * from tasks");
    return result.rows;
  } finally {
    await client.end();
  }
};

export const addColumn = async (name: string, type: string): Promise<void> => {
  const client = new Client(DB_CONFIG);
  try {
    await client.connect();
    await client.query(`ALTER TABLE tasks ADD COLUMN ${name} ${type}`);
    console.log(`Column ${name} of type ${type} added to tasks table.`);
  } finally {
    await client.end();
  }
};
