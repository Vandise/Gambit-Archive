import React from 'react';
import { Provider, connect } from 'react-redux';

class LocalsMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {

  }

  render() {

    const output = [];
    const cFrameName = this.props.currentFrame;
    const local = cFrameName ? this.props.locals[cFrameName] : {};

    console.log(local, this.props.locals);

    if (cFrameName) {
      let i = 0;
      for (let localVar in local)
      {
        output.push(
          <tr key={`stack-${i}-${cFrameName}`} id={`local-${i}`} className={i % 2 == 0 ? 'even' : 'odd'}>
            <td className='local-line-position'>{localVar}</td>
            <td>{local[localVar]}</td>
          </tr>
        );
        i++;
      }
    }

    return (
      <div className='tile is-child locals-menu'>
        <header>
          Locals
        </header>
        <div className='tile-body'>
          <table>
            <thead>
              <tr>
                <th>Identifier</th>
                <th>Value</th>
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
  locals: state.locals
});

export default connect(mapStateToProps)(LocalsMenu);