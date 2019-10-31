[%bs.raw {|require('./index.css')|}];

module App = {
  [@react.component]
  let make = () => {
    <div className="App"> <TodoList /> <PomodoroTimer /> </div>;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");