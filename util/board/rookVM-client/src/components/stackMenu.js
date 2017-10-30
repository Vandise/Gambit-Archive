import React from 'react';
import { Provider, connect } from 'react-redux';

class StackMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {

  }

  render() {

    const output = [];
    const cFrameName = this.props.currentFrame;
    const stack = cFrameName ? this.props.stacks[cFrameName] : [];

    if (cFrameName) {
      for (let i = 0; i < stack.length; i++)
      {
        output.push(
          <tr key={`stack-${i}-${cFrameName}-${stack[i]}`} id={`stack-${i}`} className={i % 2 == 0 ? 'even' : 'odd'}>
            <td className='stack-line-position'>{i}</td>
            <td>{stack[i]}</td>
          </tr>
        );
      }
    }

    return (
      <div className='tile is-child stacks-menu'>
        <header>
          Stack
        </header>
        <div className='tile-body'>
          <table>
            <thead>
              <tr>
                <th>Position</th>
                <th>Item</th>
              </tr>
            </thead>
            <tbody>
              {output}
            </tbody>
          </table>
        </div>
      </div>
    );
  }

}

const mapStateToProps = state => ({
  frames: state.frames,
  currentFrame: state.currentFrame,
  stacks: state.stacks
});

export default connect(mapStateToProps)(StackMenu);