export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'FILE',
    payload: data,
  });
};

export default {
  action: 'FILE',
  dispatch,
};