import React from 'react';
import './App.css';
import { AddNumberRoot } from './compoents/AddnumberRoot';
import { DisplayNumberRoot } from './compoents/DisplayNumberRoot';

class App extends React.Component {
  state = { number: 0 };
  render() {
    return (
      <div className="App">
        <h1>Root</h1>
        <AddNumberRoot></AddNumberRoot>
        <DisplayNumberRoot></DisplayNumberRoot>
      </div>
    );
  }
}

export default App;
