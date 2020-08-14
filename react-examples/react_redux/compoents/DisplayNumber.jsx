import React from 'react';

export default class DisplayNumber extends React.Component {
  render() {
    console.log(this.props.unit);
    return (
      <div>
        <h1>DisplayNumber</h1>
        <input type="text" value={this.props.number} readOnly></input>
        {this.props.unit}
      </div>
    );
  }
}
