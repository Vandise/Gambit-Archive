export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'SET_PROGRAM',
    payload: data,
  });
};

export default {
  action: 'SET_PROGRAM',
  dispatch,
};