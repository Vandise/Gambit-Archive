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
import StackMenu from './components/stackMenu';
import ActionsMenu from './components/actionsMenu';

// eslint-disable-next-line no-unused-vars
import Bulma from './stylesheets/bulma.scss';
import Style from './stylesheets/main.scss';

const el = document.getElementById('app');

window.reduxActions = [];

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

export const initialState = {
  message: '',
  file: { data: '' },
  logs: {},
  frames: {},
  locals: {},
  stacks: {},
  connected: false,
  currentFrame: '',
  program: 'No program loaded!',
  running: false,
  paused: false
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
    window.reduxActions.push(action);
    return {
      ...state,
      file: action.payload,
    };    
  },

  LOG: (state, action) => {
    window.reduxActions.push(action);
    const data = Object.assign({}, state.logs);
    data[action.payload.timestamp] = action.payload.data;
    return {
      ...state,
      logs: data,
    };    
  },

  PUSH_FRAME: (state, action) => {
    window.reduxActions.push(action);
    const frame = {};
    const data = Object.assign({}, state.frames);
    const locals = Object.assign({}, state.locals);
    const stacks = Object.assign({}, state.stacks);

    data[action.payload.data] = frame;
    locals[action.payload.data] = [];
    stacks[action.payload.data] = [];

    return {
      ...state,
      frames: data,
      locals: locals,
      stacks: stacks,
      currentFrame: action.payload.data
    };    
  },

  POP_FRAME: (state, action) => {
    window.reduxActions.push(action);
    const data = Object.assign({}, state.frames);
    const newFrames = {};
    let currentFrame = '';
    for (let frame in data) {
      if (frame != action.payload.data)
      {
        newFrames[frame] = data[frame];
        currentFrame = frame;
      }
    }

    const locals = Object.assign({}, state.locals);
    const stacks = Object.assign({}, state.stacks);
    locals[action.payload.data] = [];
    stacks[action.payload.data] = [];
  
    return {
      ...state,
      frames: newFrames,
      currentFrame: currentFrame,
      locals: locals,
      stacks, stacks
    };    
  },

  CONNECTED: (state, action) => {
    window.reduxActions.push(action);
    return {
      ...state,
      connected: true,
    };
  },

  INSTRUCTION_POSITION: (state, action) => {
    window.reduxActions.push(action);
    return {
      ...state,
      instructionPosition: parseInt(action.payload.data),
    };
  },

  PUSH_STACK: (state, action) => {
    window.reduxActions.push(action);
    const data = Object.assign({}, state.stacks);
    (data[state.currentFrame]).push(action.payload.data);
    const frames = Object.assign({}, state.frames);

    return {
      ...state,
      stacks: data,
      frames: frames,
    };
  },

  POP_STACK: (state, action) => {
    window.reduxActions.push(action);
    const data = Object.assign({}, state.stacks);
    (data[state.currentFrame]).pop();

    return {
      ...state,
      stacks: data,
    };
  },

  SET_PROGRAM: (state, action) => {
    return {
      ...state,
      program: action.payload.data,
    };    
  },

  TERMINATE_RUNNING: (state, action) => {
    return {
      ...state,
      running: false,
    };    
  },

  PAUSE_BOARD: (state, action) => {
    return {
      ...state,
      paused: true,
    };    
  },

  RESUME_BOARD: (state, action) => {
    return {
      ...state,
      paused: false,
    };    
  },  

  RESET: (state, action) => {
    return initialState;
  },

}, {
  message: '',
  file: { data: '' },
  logs: {},
  frames: {},
  locals: {},
  stacks: {},
  connected: false,
  instructionPosition: 0,
  currentFrame: '',
  program: '',
  running: false,
  paused: false
});


/*
  Initialize store
*/

window.initialState = initialState;

const store = createStore(counterReducer, initialState,
  compose(applyMiddleware(thunk, serverMiddleware), window.devToolsExtension ? window.devToolsExtension({ maxAge: 2000, latency: 0 }) : f => f)
);


window.store = store;

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
          Board Status
        </header>
        <div className='tile-body'>
          <p> Status: {props.connected ? 'Connected' : 'Disconnected'} </p>
          <p> Program: { props.program } </p>
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
              <StackMenu />
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
              <ActionsMenu />
            </div>

          </div>

          <LogMenu />

        </div>

      </div>
    </div>
  </Provider>, el
);


