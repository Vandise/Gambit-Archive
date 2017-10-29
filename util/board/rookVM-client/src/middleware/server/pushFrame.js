export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'PUSH_FRAME',
    payload: data,
  });
};

export default {
  action: 'PUSH_FRAME',
  dispatch,
};