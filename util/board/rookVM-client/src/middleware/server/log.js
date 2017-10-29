export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'LOG',
    payload: data,
  });
};

export default {
  action: 'LOG',
  dispatch,
};