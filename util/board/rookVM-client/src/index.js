import React from 'react';
import ReactDOM from 'react-dom';

// Standard Redux 
import thunk from 'redux-thunk';
import { Provider, connect } from 'react-redux';
import { createAction } from 'redux-actions';
import { handleActions } from 'redux-actions';
import { createStore, applyMiddleware, compose } from 'redux';
import serverMiddleware from './middleware/';


// Views
import CodeMenu from './components/codeMenu';
import LogMenu from './components/logMenu';
import FrameMenu from './components/frameMenu';

// eslint-disable-next-line no-unused-vars
import Bulma from './stylesheets/bulma.scss';
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
    return {
      ...state,
      message: action.payload.value,
    };    
  },
  FILE: (state, action) => {
    console.log(action);
    return {
      ...state,
      file: action.payload,
    };    
  },
  LOG: (state, action) => {
    const data = Object.assign({}, state.logs);
    data[action.payload.timestamp] = action.payload.data;
    return {
      ...state,
      logs: data,
    };    
  },
  PUSH_FRAME: (state, action) => {
    const frame = {
      locals: {},
      stack: {}
    };
    const data = Object.assign({}, state.frames);
    data[action.payload.data] = frame;
    return {
      ...state,
      frames: data
    };    
  },
  POP_FRAME: (state, action) => {
    const data = Object.assign({}, state.frames);
    const newFrames = {};
    for (let frame in data) {
      if (frame != action.payload.data)
      {
        newFrames[frame] = data[frame];
      }
    }
    return {
      ...state,
      frames: newFrames
    };    
  },
  CONNECTED: (state, action) => {
    return {
      ...state,
      connected: true,
    };
  },
  INSTRUCTION_POSITION: (state, action) => {
    console.log(action);
    return {
      ...state,
      instructionPosition: parseInt(action.payload.data),
    };
  },
}, {
  message: '',
  file: { data: '' },
  logs: {},
  frames: {},
  connected: false,
  instructionPosition: 0
});


/*
  Initialize store
*/
export const initialState = {
  message: '',
  file: { data: '' },
  logs: {},
  frames: {},
  connected: false,
};

const store = createStore(counterReducer, initialState,
  compose(applyMiddleware(thunk, serverMiddleware), window.devToolsExtension ? window.devToolsExtension({maxAge: 1000}) : f => f)
);


/*
  Specify the form
*/
const StatusMenu = class extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {
    // connect the socket to the server once the component mounts
    this.props.dispatch(actions.CONNECT('localhost', 44500));
  }

  render() {
    const props = this.props;
    return (
      <div className='tile is-child server-status'>
        <header>
          Server Status
        </header>
        <div className='tile-body'>
          <p> Status: {props.connected ? 'Connected' : 'Disconnected'} </p>
        </div>
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

const StatusView = connect(mapStateToProps)(StatusMenu);

/*
  Attach the view to the DOM
*/
export default ReactDOM.render(
  <Provider store={store}>
    <div className='app-container'>
      <div className='tile is-ancestor'>

        <CodeMenu />

        <div className='tile is-vertical is-8'>
          <div className='tile'>

            <div className='tile is-parent is-4'>
              <div className='tile is-child'>
                <header>
                  Stack
                </header>
                <div className='tile-body'>
                  Stack will be listed here
                </div>
              </div>
            </div>


            <div className='tile is-parent is-vertical is-4'>

              <FrameMenu />

              <div className='tile is-child'>
                <header>
                  Locals
                </header>
                <div className='tile-body'>
                  Frame Locals will be listed here
                </div>
              </div>

            </div>

            <div className='tile is-parent is-vertical is-4'>

              <StatusView />
              
              <div className='tile is-child commands'>
                <header>
                  Commands
                </header>
                <div className='tile-body'>
                  Replay/ VM commands here
                </div>
              </div>

            </div>

          </div>

          <LogMenu />

        </div>

      </div>
    </div>
  </Provider>, el
);


