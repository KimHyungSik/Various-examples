import React from 'react';

export default class AddNumber extends React.Component {
  state = { size: 1 };
  render() {
    return (
      <div>
        <h1>Add number</h1>
        <input
          type="button"
          value="+"
          onClick={() => {
            this.props.onClick(this.state.size);
          }}
        ></input>
        <input
          type="text"
          value={this.state.size}
          onChange={(e) => {
            this.setState({
              size: Number(e.target.value),
            });
          }}
        ></input>
      </div>
    );
  }
}
