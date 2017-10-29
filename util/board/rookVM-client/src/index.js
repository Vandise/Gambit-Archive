import React from 'react';
import ReactDOM from 'react-dom';

// Standard Redux 
import thunk from 'redux-thunk';
import { Provider, connect } from 'react-redux';
import { createAction } from 'redux-actions';
import { handleActions } from 'redux-actions';
import { createStore, applyMiddleware } from 'redux';
import serverMiddleware from './middleware/';

// eslint-disable-next-line no-unused-vars
import Style from './stylesheets/main.scss';

const el = document.getElementById('app');

/*
  Application Actions
*/
export const actions = {
  CONNECT: createAction('CONNECT', (host, port) => {
    return {
      host, port,
    };
  }),
};

/*
  Reducer for events received by the server
*/
export const counterReducer = handleActions({
  MESSAGE: (state, action) => {
    console.log(action);
    return {
      ...state,
      message: action.payload.value,
    };    
  },
  CONNECTED: (state, action) => {
    return {
      ...state,
      connected: true,
    };
  },
}, {
  message: '',
  connected: false,
});


/*
  Initialize store
*/
export const initialState = {
  message: '',
  connected: false,
};

const store = createStore(counterReducer, initialState,
  applyMiddleware(thunk, serverMiddleware)
);


/*
  Specify the form
*/
const Menu = class extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {
    // connect the socket to the server once the component mounts
    this.props.dispatch(actions.CONNECT('localhost', 44500));
  }

  render() {
    const props = this.props;
    if (props.connected) {
      return (
        <div className='value-container'>
          <div className='value-message'>
            <p> The current message is: {props.message} </p>
          </div>
        </div>
      );
    }
    return (
      <div>
        <p>Connecting to server...</p>
      </div>
    );
  }
};

/*
  Connect the view to listen to state changes
*/
const mapStateToProps = (state) => {
  return state;
};

const View = connect(mapStateToProps)(Menu);

/*
  Attach the view to the DOM
*/
export default ReactDOM.render(
  <Provider store={store}>
    <View />
  </Provider>, el
);


