import { addColumn } from "../tasks";

interface AddColumnArgs {
  name: string;
  type: string;
}

const parseArgs = (): AddColumnArgs => {
  const args = process.argv.slice(2);
  return {
    name: args[0],
    type: args[1],
  };
};

const main = async (): Promise<void> => {
  const args = parseArgs();
  console.log(args.name, args.type);
  await addColumn(args.name, args.type);
  console.log(`column ${args.name} of type ${args.type} added to tasks table.`);
};

if (require.main === module) {
  main();
}
