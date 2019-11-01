[%bs.raw {|require('./Input.css')|}];

let valueFromEvent = (event): string => event->ReactEvent.Form.target##value;

type state = string;

[@react.component]
let make = (~onSubmit, ~placeholder, ~label) => {
  let (text, setText) = React.useReducer((oldText, newText) => newText, "");
  <label className="Label">
    {label |> React.string}
    <input
      className="Input"
      value=text
      type_="text"
      placeholder
      onChange={event => setText(valueFromEvent(event))}
      onKeyDown={event =>
        if (ReactEvent.Keyboard.key(event) == "Enter") {
          onSubmit(text);
          setText("");
        }
      }
    />
  </label>;
};