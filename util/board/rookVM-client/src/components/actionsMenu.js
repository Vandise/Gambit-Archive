import React from 'react';
import { Provider, connect } from 'react-redux';

class ActionsMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {

  }

  runBoard() {
    return (e) => {

      e.preventDefault();

      if (!this.props.running && this.props.program != 'No program loaded!') {
        
        this.props.dispatch({ type: "RESET" });
        
        let counter = 0;
        const actionSize = window.reduxActions.length;
        
        const timer = setInterval(() => {
          if (!this.props.paused) {
            if (counter >= actionSize) {
              window.reduxActions = window.reduxActions.splice(actionSize);
              this.props.dispatch({ type: 'TERMINATE_RUNNING' });
              clearInterval(timer);
            } else {
              window.store.dispatch(window.reduxActions[counter]);
            }
            counter++;
          }
        }, 350);

      }

    };
  }

  pauseResume() {
    return (e) => {
      e.preventDefault();
      if (!this.props.paused) {
        this.props.dispatch({ type: 'PAUSE_BOARD' });
      } else {
        this.props.dispatch({ type: 'RESUME_BOARD' });
      }
    };
  }

  render() {
    return (
      <div className='tile is-child commands'>
        <header>
          Commands
        </header>
        <div className='tile-body'>
          <button className='button' onClick={this.runBoard()}>Run</button>
          <button className='button red' onClick={this.pauseResume()}>{ this.props.paused ? 'Resume' : 'Pause' }</button>
        </div>
      </div>
    );
  }

}

const mapStateToProps = state => ({
  running: state.running,
  program: state.program,
  paused: state.paused
});

export default connect(mapStateToProps)(ActionsMenu);