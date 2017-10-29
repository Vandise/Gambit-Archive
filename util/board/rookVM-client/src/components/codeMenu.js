import React from 'react';
import { Provider, connect } from 'react-redux';

class CodeMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {
    console.log('Component mounted');
  }

  render() {
    const fileLines = this.props.file.data.split('\n');
    let output = [];

    for (let i = 0; i < fileLines.length; i++)
    {
      output.push(
        <div id={`code-line-${i}`}>
          <span className='code-line-number'>{i}: </span>
          <span>{fileLines[i]}</span>
        </div>
      );
    }

    return (
      <div className='tile is-parent code-menu'>
        <div className='tile is-child'>
          <header>
            Pawn ByteCode
          </header>
          <div className='code-list'>
            <pre>
              {output}
            </pre>
          </div>
        </div>
      </div>
    );
  }

}

const mapStateToProps = state => ({
  file: state.file,
});

export default connect(mapStateToProps)(CodeMenu);