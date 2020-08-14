import { connect } from 'react-redux';
import DisplayNumber from '../compoents/DisplayNumber';

function mapReduxStateToReactProps(state) {
  return { number: state.number };
}

function mapReduxDispatchToReactProps() {
  return {};
}

export default connect(
  mapReduxStateToReactProps,
  mapReduxDispatchToReactProps
)(DisplayNumber);

// import React from 'react';
// import store from '../store';

// export default class extends React.Component {
//   constructor(props) {
//     super(props);
//     store.subscribe(() => {
//       this.setState({ number: store.getState().number });
//     });
//   }

//   render() {
//     return <DisplayNumber number={store.getState().number}></DisplayNumber>;
//   }
// }
