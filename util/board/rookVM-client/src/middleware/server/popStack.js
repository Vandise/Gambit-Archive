export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'POP_STACK',
    payload: data,
  });
};

export default {
  action: 'POP_STACK',
  dispatch,
};