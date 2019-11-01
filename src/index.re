[%bs.raw {|require('./App.css')|}];

module App = {
  [@react.component]
  let make = () => {
    <div className="App"> <TodoList /> <PomodoroTimer /> </div>;
  };
};

ReactDOMRe.renderToElementWithId(<App />, "root");