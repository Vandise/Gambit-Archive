import React from 'react';
import { Provider, connect } from 'react-redux';

class FrameMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {

  }

  render() {
    const output = [];

    let i = 0;
    for (let frame in this.props.frames)
    {
      output.push(
        <tr id={`frame-${frame}`} className={i % 2 == 0 ? 'even' : 'odd'}>
          <td className='frame-line-position'>{i}</td>
          <td>{frame}</td>
        </tr>
      );
      i++;
    }

    console.log(this.props.frames);

    return (
      <div className='tile is-child frames-menu'>
        <header>
          Frame Stack
        </header>
        <div className='tile-body'>
          <table>
            <thead>
              <tr>
                <th>Position</th>
                <th>Frame</th>
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
});

export default connect(mapStateToProps)(FrameMenu);