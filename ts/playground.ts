import { Client } from "pg";

interface Task {
  id: number;
  title: string;
  due: Date;
}

const main = async (): Promise<void> => {
  const client = new Client({
    user: "yo",
    host: "localhost",
    database: "yo",
    password: "",
    port: 5432,
  });
  await client.connect();
  const result = await client.query("select * from tasks");
  console.log(result);
};

main();