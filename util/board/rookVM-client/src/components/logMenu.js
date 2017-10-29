import React from 'react';
import { Provider, connect } from 'react-redux';

class LogMenu extends React.Component {

  constructor(props) {
    super(props);
  }

  componentDidMount() {

  }

  render() {
    const output = [];

    let i = 0;
    for (let logTimestamp in this.props.logs)
    {
      output.push(
        <tr id={`log-${logTimestamp}`} className={i % 2 == 0 ? 'even' : 'odd'}>
          <td className='log-line-timestamp'>{logTimestamp}</td>
          <td>{this.props.logs[logTimestamp]}</td>
        </tr>
      );
      i++;
    }

    return (
      <div className='tile is-parent logs-menu'>
        <div className='tile is-child'>
          <header>
            Logs
          </header>
          <div className='tile-body'>
            <table>
              <thead>
                <tr>
                  <th>Timestamp</th>
                  <th>Message</th>
                </tr>
              </thead>
              <tbody>
                {output}
              </tbody>
            </table>
          </div>
        </div>
      </div>
    );
  }

}

const mapStateToProps = state => ({
  logs: state.logs,
});

export default connect(mapStateToProps)(LogMenu);