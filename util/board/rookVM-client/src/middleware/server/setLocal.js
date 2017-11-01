export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'SET_LOCAL',
    payload: data,
  });
};

export default {
  action: 'SET_LOCAL',
  dispatch,
};