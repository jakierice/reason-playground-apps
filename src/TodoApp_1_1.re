type item = {
  title: string,
  completed: bool,
};

type state = {
  /* this is a type with a type arguement
   * similar to List<Item> in TypeScript,
   * Flow, or Java */
  items: list(item),
};