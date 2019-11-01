[%bs.raw {|require('./TodoList.css')|}];

type item = {
  id: int,
  title: string,
  completed: bool,
};

type state = {
  /* this is a type with a type arguement
   * similar to List<Item> in TypeScript,
   * Flow, or Java */
  items: list(item),
};

type action =
  | AddItem(string)
  | ToggleItem(int);

let lastId = ref(0);
let newItem = text => {
  lastId := lastId^ + 1;
  {id: lastId^, title: text, completed: false};
};

module TodoItem = {
  [@react.component]
  let make = (~item, ~onToggle) => {
    <label className="Item">
      <input
        type_="checkbox"
        checked={item.completed}
        onClick={_event => onToggle()}
        // TODO: make interactive
      />
      {item.title |> React.string}
    </label>;
  };
};

[@react.component]
let make = () => {
  let ({items}, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | AddItem(text) => {items: [newItem(text), ...state.items]}
        | ToggleItem(id) =>
          let items =
            List.map(
              item =>
                item.id === id ? {...item, completed: !item.completed} : item,
              state.items,
            );
          {items: items};
        },
      {
        items: [{id: 0, title: "Write some things to do", completed: false}],
      },
    );
  let itemCount = List.length(items);
  let itemCountLabel = itemCount == 1 ? " item" : " items";
  <div className="TodoList">
    <Card>
        <h2> {"Shit Jakie's Gotta Do" |> React.string} </h2>
        <Input onSubmit={text => dispatch(AddItem(text))} placeholder="Write something to do..." label="Todo Item Name" />
        <div className="TodoItems">
          {List.map(
             item =>
               <TodoItem
                 key={string_of_int(item.id)}
                 onToggle={() => dispatch(ToggleItem(item.id))}
                 item
               />,
             items,
           )
           |> Array.of_list
           |> React.array}
        </div>
        <div className="Footer">
          {string_of_int(itemCount) ++ itemCountLabel |> React.string}
        </div>
    </Card>
  </div>;
};