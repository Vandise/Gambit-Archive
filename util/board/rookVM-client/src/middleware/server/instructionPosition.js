export const dispatch = (action, data, dispatch) => {
  dispatch({
    type: 'INSTRUCTION_POSITION',
    payload: data,
  });
};

export default {
  action: 'INSTRUCTION_POSITION',
  dispatch,
};