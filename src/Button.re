[%bs.raw {|require('./Button.css')|}];

[@react.component]
let make = (~children, ~onClick) => {
  <button className="Button" onClick> children </button>;
};