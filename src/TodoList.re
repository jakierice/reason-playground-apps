[%bs.raw {|require('./app.css')|}];

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

let valueFromEvent = (event): string => event->ReactEvent.Form.target##value;

module Input = {
  type state = string;
  [@react.component]
  let make = (~onSubmit) => {
    let (text, setText) =
      React.useReducer((oldText, newText) => newText, "");
    <input
      value=text
      type_="text"
      placeholder="Write something to do"
      onChange={event => setText(valueFromEvent(event))}
      onKeyDown={event =>
        if (ReactEvent.Keyboard.key(event) == "Enter") {
          onSubmit(text);
          setText("");
        }
      }
    />;
  };
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
    <div className="Card">
      <h2> {"Shit Jakie's Gotta Do" |> React.string} </h2>
      // <button onClick={_event => dispatch(AddItem)}>
      //   {"Add a todo" |> React.string}
      // </button>
      <Input onSubmit={text => dispatch(AddItem(text))} />
      // <div className="Items"> {"Nothing" |> React.string} </div>
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
    </div>
  </div>;
};