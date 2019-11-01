type state = {
  remainingSeconds: int,
  isTicking: bool,
};

type action =
  | Start
  | Stop
  | SetTimerMinutes(string)
  | Reset
  | Tick;

module Button = {
  [@react.component]
  let make = (~children, ~onClick) => {
    <button onClick> children </button>;
  };
};

let padNumber = numString =>
  if (numString |> int_of_string < 10) {
    "0" ++ numString;
  } else {
    numString;
  };

let formatTime = seconds => {
  let mins = seconds / 60;
  let minsString = mins |> string_of_int |> padNumber;
  let seconds = seconds mod 60;
  let secondsString = seconds |> string_of_int |> padNumber;
  minsString ++ ":" ++ secondsString;
};

let convertMinutesToSeconds = minutes => minutes * 60;

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      // reduce function
      (state, action) =>
        switch (action) {
        | Start => {...state, isTicking: true}
        | Stop => {...state, isTicking: false}
        | SetTimerMinutes(minutes) => {...state, remainingSeconds: minutes |> int_of_string |> convertMinutesToSeconds}
        | Reset => {...state, remainingSeconds: 30}
        | Tick =>
          state.isTicking && state.remainingSeconds > 0
            ? {...state, remainingSeconds: state.remainingSeconds - 1} : state
        },
      // initial state
      {
        isTicking: false,
        remainingSeconds: convertMinutesToSeconds(45),
      },
    );

  React.useEffect0(() => {
    let timerId = Js.Global.setInterval(() => dispatch(Tick), 1000);
    Some(() => Js.Global.clearInterval(timerId));
  });

  <div className="PomodoroTimer">
    <div className="Card">
      <h2>
        {"There are "
         ++ formatTime(state.remainingSeconds)
         ++ " on the clock!"
         |> React.string}
      </h2>
      <Input onSubmit={(value) => dispatch(SetTimerMinutes(value))} />
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