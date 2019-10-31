[%bs.raw {|require('./app.css')|}];

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

[@react.component]
let make = () => {
  let ({items}, dispatch) =
    React.useReducer(
      (state, action) => state,
      {items: [{title: "Write some things to do", completed: false}]},
    );
  let numItems = List.length(items);
  <div className="App">
    <div className="Title"> {"What to do" |> React.string} </div>
    <div className="Items"> {"Nothing" |> React.string} </div>
    <div className="Footer">
      (string_of_int(numItems) ++ " items" |> React.string)
    </div>
  </div>;
};