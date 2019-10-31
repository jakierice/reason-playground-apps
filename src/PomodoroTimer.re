type state = {
  seconds: int,
  isTicking: bool,
};

type action =
  | Start
  | Stop
  | Reset
  | Tick;

module Button = {
  [@react.component]
  let make = (~children, ~onClick) => {
    <button onClick> children </button>;
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      // reduce function
      (state, action) =>
        switch (action) {
        | Start => {...state, isTicking: true}
        | Stop => {...state, isTicking: false}
        | Reset => {...state, seconds: 30}
        | Tick =>
          state.isTicking && state.seconds > 0
            ? {...state, seconds: state.seconds - 1} : state
        },
      // initial state
      {isTicking: false, seconds: 30},
    );

  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div className="PomodoroTimer">
    <div className="Card">
      <h2>
        {"There are "
         ++ string_of_int(state.seconds)
         ++ " on the clock!"
         |> React.string}
      </h2>
      {state.isTicking
         ? <Button onClick={_event => dispatch(Stop)}>
             {"Stop" |> React.string}
           </Button>
         : <>
             <Button onClick={_event => dispatch(Start)}>
               {"Start" |> React.string}
             </Button>
             <Button onClick={_event => dispatch(Reset)}>
               {"Reset" |> React.string}
             </Button>
           </>}
    </div>
  </div>;
};