let valueFromEvent = (event): string => event->ReactEvent.Form.target##value;

type state = string;

[@react.component]
let make = (~onSubmit) => {
  let (text, setText) = React.useReducer((oldText, newText) => newText, "");
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