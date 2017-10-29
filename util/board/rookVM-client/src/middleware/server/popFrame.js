export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'POP_FRAME',
    payload: data,
  });
};

export default {
  action: 'POP_FRAME',
  dispatch,
};