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

export const showAllTasks = async (): Promise<void> => {
  const tasks = await getAllTasks();
  console.log(tasks);
};

export const addColumn = async (
  table: string,
  name: string,
  type: string,
): Promise<void> => {
  const client = new Client(DB_CONFIG);
  try {
    await client.connect();
    await client.query(`ALTER TABLE ${table} ADD COLUMN ${name} ${type}`);
    console.log(`Column ${name} of type ${type} added to ${table} table.`);
  } finally {
    await client.end();
  }
};

export const setTags = async (id: number, tags: string[]): Promise<void> => {
  const client = new Client(DB_CONFIG);
  try {
    await client.connect();
    await client.query(
      `UPDATE tasks SET tags = '${JSON.stringify(tags)}' WHERE id = ${id}`,
    );
  } catch (error) {
    console.error("error setting tags: ", error);
  } finally {
    await client.end();
  }
};
