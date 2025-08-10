import { addColumn } from "../tasks";

interface AddColumnArgs {
  table: string;
  column: string;
  type: string;
}

const parseArgs = (): AddColumnArgs => {
  const args = process.argv.slice(2);
  return {
    table: args[0],
    column: args[1],
    type: args[2],
  };
};

const main = async (): Promise<void> => {
  const args = parseArgs();
  console.log(args.column, args.type);
  await addColumn(args.table, args.column, args.type);
  console.log(
    `column ${args.column} of type ${args.type} added to tasks table.`,
  );
};

if (require.main === module) {
  main();
}
