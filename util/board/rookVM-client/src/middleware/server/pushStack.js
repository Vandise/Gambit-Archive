export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'PUSH_STACK',
    payload: data,
  });
};

export default {
  action: 'PUSH_STACK',
  dispatch,
};