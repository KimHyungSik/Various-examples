import { connect } from 'react-redux';
import AddNumber from '../compoents/AddNumber';

function mapDispatchToProps(dispatch) {
  return {
    onClick: (size) => {
      dispatch({ type: 'INCREMENT', size });
    },
  };
}

export default connect(null, mapDispatchToProps)(AddNumber);
